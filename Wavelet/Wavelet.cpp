#include "../plugin.hpp"
#include "Haar.hpp"

#define NLAYERS 4
#define BLOCK (1<<NLAYERS)
#define RING 5

#define EPSILON 1.0e-6
#define THRESHOLD_MAX 1.0f

struct Wavelet : Module {
public:
	enum ParamIds {
		DETAIL1_PARAM,
		DETAIL2_PARAM,
		DETAIL3_PARAM,
		DETAIL4_PARAM,
		APPROX_PARAM,
		ALGORITHM_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		INPUT_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	enum class Algorithm : unsigned {
		Scale = 2,
		Bypass = 1,
		Threshold = 0
	};

private:
	Algorithm algorithm() {
		auto value = unsigned(params[ALGORITHM_PARAM].getValue());
		try {
			return static_cast<Algorithm>(value);
		}
		catch(...) {
			return Algorithm::Bypass;
		}
	}
	haar::Haar wavelet;
	float * buffer;
	float * outs;
	float * thresholds;

	float * ring;
	unsigned offset;
	unsigned ringOffset;
public:

	Wavelet()  : wavelet(NLAYERS), offset(0), ringOffset(0) {
		buffer = new float[BLOCK];
		outs = new float[BLOCK];
		thresholds = new float[NLAYERS+1];
		ring = new float[RING];

		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(DETAIL1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(DETAIL2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(DETAIL3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(DETAIL4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(APPROX_PARAM, 0.f, 1.f, 0.f, "");
		configParam(ALGORITHM_PARAM, 0.f, 2.f, 0.f, "Algorithm", "",0,1,0);
		INFO("Wavelet module wrapper class initialised");
	}

	virtual ~Wavelet() {
		delete [] buffer;
		delete [] outs;
		delete [] thresholds;
		delete [] ring;
	}

	void process(const ProcessArgs& args) override {
		float input = inputs[INPUT_INPUT].getVoltage();
		auto alg=algorithm();
		//INFO("Algorithm is %d",alg);

			for(auto i=0;i<NLAYERS+1;i++) thresholds[i]=params[i].getValue();


			input = clamp(input,-5.0f,5.0f);
			buffer[offset++]=input;
			if(offset==BLOCK) {
				wavelet.analyse(buffer);
				ring[ringOffset]=wavelet.absMaximum();
				ringOffset=(ringOffset+1)%RING;
				auto ringMax = *std::max_element(ring,ring+RING);
				switch(alg) {
				case Algorithm::Threshold:
					wavelet.threshold(thresholds,ringMax+EPSILON);
					break;
				case Algorithm::Bypass:
					break;
				case Algorithm::Scale:
					wavelet.scale(thresholds);
					break;
				}
				wavelet.threshold(thresholds,ringMax+EPSILON);
				wavelet.synthesise(outs);
				offset=0;
			}
			float output = (alg==Algorithm::Bypass) ? input : clamp(outs[offset],-5.0f,5.0f);
			outputs[OUTPUT_OUTPUT].setVoltage(output);
		}

};


struct WaveletWidget : ModuleWidget {
	WaveletWidget(Wavelet* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Wavelet.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.137, 28.726)), module, Wavelet::DETAIL1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(21.075, 28.726)), module, Wavelet::DETAIL2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.137, 42.711)), module, Wavelet::DETAIL3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(21.075, 42.711)), module, Wavelet::DETAIL4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.137, 56.696)), module, Wavelet::APPROX_PARAM));
		addParam(createParam<CKSSThree>(mm2px(Vec(4.764, 72.534)), module, Wavelet::ALGORITHM_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.52, 104.699)), module, Wavelet::INPUT_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(21.96, 104.699)), module, Wavelet::OUTPUT_OUTPUT));
	}
};


Model* modelWavelet = createModel<Wavelet, WaveletWidget>("Wavelet");
