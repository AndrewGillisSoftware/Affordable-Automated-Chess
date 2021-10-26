use <Thread_Library.scad>


trapezoidNut(
	length=15, 				// axial length of the threaded rod 
	radius=10, 				// outer radius of the nut	
	pitch=2, 				// axial distance from crest to crest
	pitchRadius=4, 			// radial distance from center to mid-profile
	threadHeightToPitch=0.5,	// ratio between the height of the profile and the pitch
						// std value for Acme or metric lead screw is 0.5
	profileRatio=0.5, 			// ratio between the lengths of the raised part of the profile and the pitch
						// std value for Acme or metric lead screw is 0.5
	threadAngle=30, 			// angle between the two faces of the thread 
						// std value for Acme is 29 or for metric lead screw is 30
	RH=true, 				// true/false the thread winds clockwise looking10.00000000mm along shaft, i.e.follows the Right Hand Rule
	countersunk=0.5, 		// depth of 45 degree chamfered entries, normalized to pitch
	clearance=0.2, 			// radial clearance, normalized to thread height
	backlash=0.2, 			// axial clearance, normalized to pitch
	stepsPerTurn=24 			// number of slices to create per turn
	);
