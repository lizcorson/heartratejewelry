sidelength = 35;
shelfheight = 5;
wallthick = 2.5;
ringheight = 5;
ringOD = 10;
ringID = 3;
fnval = 100;
*translate([wallthick,wallthick+1,wallthick]) powercell();
*translate([wallthick,wallthick+1,wallthick]) battery();
*translate([wallthick,wallthick+1,wallthick]) promini();

*rotate([0,90,0]) button();

 heartshelforig();
module powercell() {
    color([1,0,0]) cube([26.16,24.13,1]);
}
module battery() {
    color([0,0,0]) cube([25,35,5]);
}

module promini() {
    color([0,0,1]) cube([42,18,.8]);
}

module button() { 
    cylinder([wallthick,6.8,6.8],$fn=fnval);
}

module support(l, w, h) {
       polyhedron(points=[
               [0,0,h],           // 0    front top corner
               [w,0,h],[0,0,0],   // 1, 2 front left & right bottom corners
               [0,l,h],           // 3    back top corner
               [w,l,h],[0,l,0]    // 4, 5 back left & right bottom corners
       ], faces=[ // points for all faces must be ordered clockwise when looking in
               [0,2,1],    // top face
               [3,4,5],    // base face
               [0,1,4,3],  // h face
               [1,2,5,4],  // w face
               [0,3,5,2],  // hypotenuse face
       ]);
}

module prismorig(l, w, h) {
       polyhedron(points=[
               [0,0,h],           // 0    front top corner
               [0,0,0],[w,0,0],   // 1, 2 front left & right bottom corners
               [0,l,h],           // 3    back top corner
               [0,l,0],[w,l,0]    // 4, 5 back left & right bottom corners
       ], faces=[ // points for all faces must be ordered clockwise when looking in
               [0,2,1],    // top face
               [3,4,5],    // base face
               [0,1,4,3],  // h face
               [1,2,5,4],  // w face
               [0,3,5,2],  // hypotenuse face
       ]);
}

 module heartshelf() {
     union() {
        shortside = sidelength-wallthick*2;
        cube([shortside,shortside,maxheight-wallthick]);
        translate([0,shortside,0]) cube([shortside,wallthick,maxheight-wallthick]);
        translate([shortside,0,0]) cube([wallthick,shortside,maxheight-wallthick]);
        translate([shortside/2,shortside+wallthick*2,0]) cylinder(maxheight-wallthick,shortside/2,shortside/2,false,$fn=fnval);
        translate([shortside+wallthick*2,shortside/2,0]) cylinder(maxheight-wallthick,shortside/2,shortside/2,false,$fn=fnval);
    }
}

 module heartshelforig() {
    translate([-wallthick,-wallthick,0]) union() {
        shortside = sidelength-wallthick*2;
        translate([wallthick,wallthick,0]) cube([shortside,shortside,shelfheight-wallthick]);
        translate([wallthick,sidelength-wallthick,0]) cube([shortside,wallthick,shelfheight-wallthick]);
        translate([sidelength-wallthick,wallthick,0]) cube([wallthick,shortside,shelfheight-wallthick]);
        translate([wallthick+shortside/2,shortside+wallthick*2,0]) cylinder(shelfheight-wallthick,shortside/2,shortside/2,false,$fn=fnval);
        translate([shortside+wallthick*2,wallthick+shortside/2,0]) cylinder(shelfheight-wallthick,shortside/2,shortside/2,false,$fn=fnval);
    }
}