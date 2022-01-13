#include "../../inc/imagestack/PetteriAimonenFocusImageStacker.h"

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
	FocusStack stack;

	// Output file options
	stack.set_inputs(inImgPaths);
	stack.set_output(outImgPath);
	stack.set_jpgquality(100);
	stack.set_verbose(false);

	// Image alignment options
	int flags = FocusStack::ALIGN_DEFAULT;
	stack.set_align_flags(flags);

	// Image merge options
	//stack.set_consistency(std::stoi(options.get_arg("--consistency", "2")));
	//stack.set_denoise(std::stof(options.get_arg("--denoise", "1.0")));

	// Depth map generation options
	//stack.set_depthmap_smooth_xy(std::stof(options.get_arg("--depthmap-smooth-xy", "16")));
	//stack.set_depthmap_smooth_z(std::stof(options.get_arg("--depthmap-smooth-z", "32")));
	//stack.set_depthmap_threshold(std::stoi(options.get_arg("--depthmap-threshold", "16")));
	//stack.set_halo_radius(std::stof(options.get_arg("--halo-radius", "20")));
	//stack.set_3dviewpoint(options.get_arg("--3dviewpoint", "0.5:1.0:0.5:2.0"));

	// Performance options
	/*if(options.has_flag("--threads")){
		stack.set_threads(std::stoi(options.get_arg("--threads")));
	}*/

	//stack.set_disable_opencl(options.has_flag("--no-opencl"));

	// Information options (some are handled at beginning of this function)
	//stack.set_verbose(options.has_flag("--verbose"));

	if(!stack.run()){
		std::printf("\nError exit due to failed steps\n");
	}

	std::printf("\rSaved to %-40s\n", stack.get_output().c_str());

	if(stack.get_depthmap() != ""){
		std::printf("\rSaved depthmap to %s\n", stack.get_depthmap().c_str());
	}

	if(stack.get_3dview() != ""){
		std::printf("\rSaved 3D preview to %s\n", stack.get_3dview().c_str());
	}
}
