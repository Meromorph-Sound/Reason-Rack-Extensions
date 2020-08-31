# Reason-Rack-Extensions
Rack Extensions for Propellerheads Reason DAW (version 11+) 

*All of these extensions are in development and not yet formally released as Reason extensions*

## Follower
A very simple envelope generator.  Input andf output signal are **mono**.  Generates the envelope of an input signal using a configurable algorithm, and a gate CV, based on a configurable threshold.  The algorithm is

    Input -->-- Rectifier -->-- single-pole IIR filter -->-- output

### Signals

* Inputs: 
  - the signal to generate an envelope for
* Outputs:
  - the input's envelope
  - a gate CV, set to 1 when the envelope value exceeds a specified threshold, 0 otherwise
	
### Controls

* **Rectification**: choose one of three rectification methods to apply to the incoming signal
  - **Half-wave** : half-wave rectification: keep positive values, set negative values to 0
  - **Full-wave** : full-wave rectification: compute the signal's absolute magnitude
  - **Square**    : squaring: compute the signal's square

* **Learning rate**: sets the decay rate of the single pole IIR filter used to generate the envelope from the rectified signal
  - Ranges from 0 to 1
  - 0 = ignore new information; gives constant output
  - 1 = no filtering; gives pure rectified output 

* **Threshold**: the signal level at which to threshold the envelope in order to determine whether to set the gate CV.  
  - Ranges from (just above) 0 to very large (of the order of 100).  
  - Defaults to 0.5
  - *NB Scale is highly non-linear*
