// Copyright (c) 2022 András Lehotay-Kéry

#include "../../inc/imagestack/PetteriAimonenFocusImageStacker.h"
#include "../../inc/util/Timer.h"

#include <options.hh>
#include <focusstack.hh>
#include <opencv2/core.hpp>

#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;
using namespace focusstack;

PetteriAimonenFocusImageStacker::PetteriAimonenFocusImageStacker(){
	// NOOP
}

PetteriAimonenFocusImageStacker::~PetteriAimonenFocusImageStacker(){
	// NOOP
}

void PetteriAimonenFocusImageStacker::stackImages(
	const std::vector<std::string> inImgPaths,
	const std::string outImgPath
){
	Timer timer;
	timer.start();

	FocusStack stack;

	// Output file options
	stack.set_inputs(inImgPaths);
	stack.set_output(outImgPath);
	stack.set_jpgquality(100);
	stack.set_verbose(false);

	// Image alignment options
	int flags = FocusStack::ALIGN_DEFAULT;
	stack.set_align_flags(flags);

	if(!stack.run()){
		std::cout << "Error exit due to failed steps" << std::endl;
	}

	std::printf("\rSaved to %-40s\n", stack.get_output().c_str());

	if(stack.get_depthmap() != ""){
		std::cout << "Saved depthmap to " << stack.get_depthmap() << std::endl;
	}

	if(stack.get_3dview() != ""){
		std::cout << "Saved 3D preview to " << stack.get_3dview() << std::endl;
	}

	cout << "Overall TIME: " << timer.getElapsedMillis().count() << "ms" << endl;
}
