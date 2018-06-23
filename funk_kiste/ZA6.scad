module kiste(x,y,z){ difference() {
    color([0.1,0.4,0.0]) cube([x,y,z]);
    color([0.5,0.5,0.5]) translate([30,30,40]) cube([x-60,y-60,z]);
}
difference() {
color([0.1,0.4,0.0]) translate([0,y,z]) cube([x,30,y]);
color([0.5,0.5,0.5]) translate([10,y-10,z+10]) cube([x-20,30,y-20]);
}
}

//TODO Nachmessen, Rückseite
module 2m_TXRX(x,y,z) {
translate([x,y,z]) {
 color([0.1,0.1,0.1]) cube([335,130,325]);
    
 translate([140,75,325]) color([0.7,0.7,0.7]) cylinder(50,r=30,center=true);
 translate([220,50,325]) color([0.7,0.7,0.7]) cylinder(40,r=10,center=true);
 translate([260,50,325]) color([0.7,0.7,0.7]) cylinder(40,r=10,center=true);
 
 translate ([10,20,325]) color([0.2,0.0,0.8]) cube([80,100,2]);
    
}
}

module bleiakku(x,y,z) {
    translate([x,y,z]) rotate([90,0,0]) { 
        color([0,0,0]) cube([150,65,95]);
        
        translate([5,55,95]) color([0.5,0.5,0.5]) cube([10,5,6]);    
        translate([0,35,95]) color([1,0,0]) cube([10,30,1]); 
        
        translate([5,5,95]) color([0.5,0.5,0.5]) cube([10,5,6]);    
        translate([0,0,95]) color([0,0,1]) cube([10,30,1]); 
    }
}

module KWTXRX(x,y,z) {
translate([x,y,z]) {
    difference() {
        color([0.1,0.1,0.1]) cube([240,93,240]);
        color([0.2,0.2,0.2]) translate([10,79,0]) cube([220,15,150]);
    }
    for(i = [1:11])
   color([0.4,0.4,0.4]) translate([i*20,79,0]) cube([2,14,150]);
    
   translate([160,30,240]) color([0.7,0.7,0.7]) cylinder(50,r=23,center=true);
  translate([12,12,240]) color([0.7,0.7,0.7]) cylinder(5,d=16,center=true);
 translate ([20,60,240]) color([0.2,0.0,0.8]) cube([150,25,2]);
    
    translate ([205,50,-15]) color([0.7,0.7,0.7]) cube([15,20,15]);
    
   translate([32,55,-5]) color([0.7,0.7,0.7]) cylinder(5,d=15,center=true);
}
}

//TODO Rückseite
module KWTUNER(x,y,z) {
translate([x,y,z]) {
    
        color([0.1,0.1,0.1]) cube([240,93,240]);
    
 translate ([50,55,240]) color([0.2,0.0,0.8]) cube([175,35,2]);
    
    translate ([205,50,-15]) color([0.7,0.7,0.7]) cube([15,20,15]);
    
   translate([32,55,-5]) color([0.7,0.7,0.7]) cylinder(5,d=15,center=true);
}
}

module FAN() {
    $fn=10;
  difference()
    {
    linear_extrude(height=25, center = true, convexity = 4, twist = 0)
      difference()
        {
        //overall outside
        square([120,120],center=true);
        //main inside bore, less hub
        difference()
          {
          circle(r=114/2,center=true);
          //hub. Just imagine the blades, OK?
          circle(r=31.5/2,center=true);
          }
        //Mounting holes
        translate([+50,+50]) circle(r=3.4/2,h=25+0.2,center=true);
        translate([+50,-50]) circle(r=3.4/2,h=25+0.2,center=true);
        translate([-50,+50]) circle(r=3.4/2,h=25+0.2,center=true);
        translate([-50,-50]) circle(r=3.4/2,h=25+0.2,center=true);
        //Outside Radii
        translate([+60,+60]) difference()
          {
          translate([-4.9,-4.9]) square([5.1,5.1]);
          translate([-5,-5]) circle(r=5);
          }
        translate([+60,-60]) difference()
          {
          translate([-4.9,-0.1]) square([5.1,5.1]);
          translate([-5,+5]) circle(r=5);
          }
        translate([-60,+60]) difference()
          {
          translate([-0.1,-4.9]) square([5.1,5.1]);
          translate([+5,-5]) circle(r=5);
          }
        translate([-60,-60]) difference()
          {
          translate([-0.1,-0.1]) square([5+0.1,5+0.1]);
          translate([5,5]) circle(r=5);
          }
      } //linear extrude and 2-d difference
    //Remove outside ring
    difference()
      {
      cylinder(r=176/2,h=25-3.6-3.6,center=true);
      cylinder(r=128/2,h=25-3.6-3.6+0.2,center=true);
      }      
    }// 3-d difference

    //Seven Blades
    linear_extrude(height=24, center = true, convexity = 4, twist = -30)
      for(i=[0:9])
        rotate((360*i)/9)
          translate([0,-1.5/2]) #square([114/2-0.75,1.5]);
}

module CTRL_PANEL(x,y,z) {
    translate([x,y,z]) {
        color([0.25,0.2,0.05]) cube([75,125,3]);

    translate([25,25,3]) color([0.7,0.7,0.7]) cylinder(25,r=10,center=true);
 translate([50,25,3]) color([0.7,0.7,0.7]) cylinder(15,r=10,center=true);
        
  translate([25,50,3]) color([0.7,0.7,0.7]) cylinder(25,r=10,center=true);
 translate([50,50,3]) color([0.7,0.7,0.7]) cylinder(15,r=10,center=true);       
    }
}

module 2mEndstufe(x,y,z) {
    translate([x,y,z]) {
        color([0.4,0.4,0.4]) cube([160,95,190]);
}
}

module 70cmEndstufe(x,y,z) {
    translate([x,y,z]) {
        color([0.4,0.4,0.4]) cube([180,125,80]);
}
}


kiste(600,300,400);
2m_TXRX(230,35,50);
bleiakku(30,270,30);
bleiakku(225,270,30);
bleiakku(420,270,30);
KWTXRX(35,180,125);
KWTUNER(280,180,125);
translate([90,90,360]) color([0.1,0.8,0.1])FAN();
CTRL_PANEL(155,35,370);
2mEndstufe(35,35,50);
70cmEndstufe(35,35,250);