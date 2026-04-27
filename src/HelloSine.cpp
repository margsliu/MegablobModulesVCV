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

	float phase = 0.f;

	HelloSine() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		// Use a log scale for the knob, with the range being 20Hz-20000Hz
		configParam(FREQ_PARAM, std::log2(20.f), std::log2(20000.f), std::log2(440.f), "Frequency", " Hz");
		// Have the VCV Rack tooltip display in Hz
        paramQuantities[FREQ_PARAM]->displayBase = 2.f;
		configOutput(OUT_OUTPUT, "Sine");
	}

	void process(const ProcessArgs& args) override {
		// Read knob as log2 value and convert back to Hz
		float freq = std::pow(2.f, params[FREQ_PARAM].getValue());

		// Advance phase
		phase += freq * args.sampleTime;
		if (phase >= 1.f) phase -= 1.f;

		// Output sine wave (-5V to +5V)
		outputs[OUT_OUTPUT].setVoltage(5.f * std::sin(2.f * M_PI * phase));
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

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.155f, 42.406f)), module, HelloSine::FREQ_PARAM));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.155f, 89.667f)), module, HelloSine::OUT_OUTPUT));
	}
};


Model* modelHelloSine = createModel<HelloSine, HelloSineWidget>("HelloSine");