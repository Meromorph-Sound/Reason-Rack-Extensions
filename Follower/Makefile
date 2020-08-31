SDK_HOME := $(HOME)/Reason/SDK
RENDERER := $(SDK_HOME)/RE2DRender.app/Contents/MacOS/Re2DRender

.PHONY: gui
gui:
	$(RENDERER) GUI2D GUI

.PHONY: build
build:
	python build45.py local45 Testing

all: gui build
