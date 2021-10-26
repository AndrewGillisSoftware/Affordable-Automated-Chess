use <Thread_Library_Throated.scad>
use <MCAD/involute_gears.scad>

numberTeeth=20;
pitchRadius=120;
thickness=30;


radius=60;
pitch=2*3.1415*pitchRadius/numberTeeth;

length=pitch*4;
position=length/2;

angle=-360*$t;
offset=1;

distance=radius+pitchRadius-0.5*pitch;

translate([0,15,0])
{
translate([0,0,-position])
rotate([0,0,180+angle])
#trapezoidThreadThroated( 
	length=length, 			// axial length of the threaded rod
	pitch=pitch,				// axial distance from crest to crest
	pitchRadius=radius, 		// radial distance from center to mid-profile
	throatDistance=distance, 	// radial distance to center of curvature of throat 
	throatRadius=pitchRadius, 	// radius of curvature of throat
	throatHeight=position,		// axial distance to center of curvature of throat
	threadHeightToPitch=0.5, 	// ratio between the height of the profile and the pitch
						// std value for Acme or metric lead screw is 0.5
	profileRatio=0.5,			// ratio between the lengths of the raised part of the profile and the pitch
						// std value for Acme or metric lead screw is 0.5
	threadAngle=22.5, 			// angle between the two faces of the thread
						// std value for Acme is 29 or for metric lead screw is 30
	RH=true, 				// true/false the thread winds clockwise looking along shaft, i.e.follows the Right Hand Rule
	clearance=0.3, 			// radial clearance, normalized to thread height
	backlash=0.1, 			// axial clearance, normalized to pitch
	stepsPerTurn=24,			// number of slices to create per turn
	showVertices=false
	);


translate([-thickness/2,-distance,0])
rotate([0,90,0])
rotate([0,0,offset-angle/numberTeeth])
gear ( 
	number_of_teeth=numberTeeth,
	circular_pitch=360*pitchRadius/numberTeeth,
	pressure_angle=22.5,
	clearance = 0.2,
	gear_thickness=thickness,
	rim_thickness=thickness,
	rim_width=5,
	hub_thickness=thickness,
	hub_diameter=10,
	bore_diameter=5,
	circles=0,
	backlash=0.1,
	twist=-pitchRadius/radius,
	involute_facets=0,
	flat=false);
}
