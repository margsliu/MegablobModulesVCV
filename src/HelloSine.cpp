#include "plugin.hpp"


struct HelloSine : Module {
	enum ParamId {
		FREQ_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		INPUTS_LEN
	};
	enum OutputId {
		OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	HelloSine() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(FREQ_PARAM, 0.f, 1.f, 0.f, "");
		configOutput(OUT_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
	}
};


struct HelloSineWidget : ModuleWidget {
	HelloSineWidget(HelloSine* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/HelloSine.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.155, 42.406)), module, HelloSine::FREQ_PARAM));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.155, 89.667)), module, HelloSine::OUT_OUTPUT));
	}
};


Model* modelHelloSine = createModel<HelloSine, HelloSineWidget>("HelloSine");