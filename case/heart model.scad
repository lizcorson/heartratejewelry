sidelength = 35;
maxheight = 30;
shelfheight = 3;
wallthick = 2.5;
ringheight = 5;
ringOD = 10;
ringID = 3;
fnval = 100;

union() {
    difference() {
        heartshell();
        union() {
            translate([0,10,wallthick+1]) microusbport();
            translate([20,0,wallthick+7]) button();
            translate([0,20,wallthick+7]) powerswitch();
        }
    }
    translate([sidelength+wallthick-.3,sidelength+wallthick-.3,maxheight/4]) ring();
    translate([wallthick,wallthick+7,wallthick+18]) shelf(20,3,3);
    translate([20+wallthick+7,wallthick,wallthick+18]) rotate([0,0,90]) shelf(20,3,3);
    *translate([0,0,wallthick]) standoff();
    translate([60,0,0]) heartshelf();
    
    // show models of components
    *translate([wallthick,wallthick+1,wallthick]) powercell();
    *translate([wallthick,wallthick+1,wallthick]) battery();
    
}




*translate([10,10,maxheight]) neopixel();
*translate([10,25,maxheight]) neopixel();
*translate([25,10,maxheight]) neopixel();
*translate([25,25,maxheight]) neopixel();
*translate([18,40,maxheight]) neopixel();
*translate([40,18,maxheight]) neopixel();

module outerheart() {
    union() {
        cube([sidelength,sidelength,maxheight]);
        translate([sidelength,sidelength/2,0]) cylinder(maxheight,sidelength/2,sidelength/2,false,$fn=fnval);
        translate([sidelength/2,sidelength,0]) cylinder(maxheight,sidelength/2,sidelength/2,false,$fn=fnval);
    }
}

module innerheart() {
    union() {
        shortside = sidelength-wallthick*2;
        translate([wallthick,wallthick,wallthick]) cube([shortside,shortside,maxheight-wallthick]);
        translate([wallthick,sidelength-wallthick,wallthick]) cube([shortside,wallthick,maxheight-wallthick]);
        translate([sidelength-wallthick,wallthick,wallthick]) cube([wallthick,shortside,maxheight-wallthick]);
        translate([wallthick+shortside/2,shortside+wallthick*2,wallthick]) cylinder(maxheight-wallthick,shortside/2,shortside/2,false,$fn=fnval);
        translate([shortside+wallthick*2,wallthick+shortside/2,wallthick]) cylinder(maxheight-wallthick,shortside/2,shortside/2,false,$fn=fnval);
    }
}

module heartshell() {
    difference() {
        outerheart();
        innerheart();
    }
}

module ring() {
difference() {
    resize(newsize=[ringOD,ringOD,ringheight]) sphere(ringOD,$fn=fnval);
    cylinder(ringheight*2,ringID,ringID,true,$fn=fnval);
}
}

module neopixel() {
color([1,1,1]) intersection() {
        translate([-4,-5,0]) cube([8,10,3]);
        cylinder(3,5,5);
    }
}

module microusbport() {
    cube([3,7,1.95]);
}

module powerswitch() {
    cube([wallthick,8.55,3.75]);
}

module button() { 
    rotate([0,90,90]) cylinder(wallthick+1,3.4,3.4,$fn=fnval);
}

module powercell() {
    color([1,0,0]) cube([26.16,24.13,1]);
}
module battery() {
    color([0,0,0]) cube([25,35,5]);
}

module shelf(l, w, h) {
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
    //credit: https://github.com/dannystaple/OpenSCAD-Parts-Library/blob/master/prism.scad
}

module standoff() {
    cylinder(2,1.45,1.45,$fn=fnval);
}

 module heartshelf() {
    difference() {
        translate([-wallthick,-wallthick,0]) union() {
        shortside = sidelength-wallthick*2;
        translate([wallthick,wallthick,0]) cube([shortside,shortside,shelfheight-wallthick]);
        translate([wallthick,sidelength-wallthick,0]) cube([shortside,wallthick,shelfheight-wallthick]);
        translate([sidelength-wallthick,wallthick,0]) cube([wallthick,shortside,shelfheight-wallthick]);
        translate([wallthick+shortside/2,shortside+wallthick*2,0]) cylinder(shelfheight-wallthick,shortside/2,shortside/2,false,$fn=fnval);
        translate([shortside+wallthick*2,wallthick+shortside/2,0]) cylinder(shelfheight-wallthick,shortside/2,shortside/2,false,$fn=fnval);
    }
    translate([13,5,0]) cylinder(shelfheight,2,2);
}
}

