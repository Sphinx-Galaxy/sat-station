module kiste(x,y,z){ difference() {
    color([0.1,0.4,0.0]) cube([x,y,z]);
    color([0.5,0.5,0.5]) translate([30,30,40]) cube([x-60,y-60,z]);
}
difference() {
color([0.1,0.4,0.0]) translate([0,y,z]) cube([x,30,y]);
color([0.5,0.5,0.5]) translate([10,y-10,z+10]) cube([x-20,20,y-20]);
}
}

module 2m_TXRX(x,y,z) {
translate([x,y,z]) {
 color([0.1,0.1,0.1]) cube([300,140,240]);
    
 translate([140,75,240]) color([0.7,0.7,0.7]) cylinder(40,r=30,center=true);
 translate([220,50,240]) color([0.7,0.7,0.7]) cylinder(25,r=10,center=true);
 translate([260,50,240]) color([0.7,0.7,0.7]) cylinder(15,r=10,center=true);
 
 translate ([10,20,240]) color([0.2,0.0,0.8]) cube([80,100,2]);
    
}
}

module bleiakku(x,y,z) {
    translate([x,y,z]) { 
        color([0,0,0]) cube([150,64,94]);
        
        translate([5,55,95]) color([0.5,0.5,0.5]) cube([10,5,6]);    
        translate([0,34,95]) color([1,0,0]) cube([10,30,1]); 
        
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
    
   translate([160,30,240]) color([0.7,0.7,0.7]) cylinder(25,r=23,center=true);
  translate([12,12,240]) color([0.7,0.7,0.7]) cylinder(5,d=16,center=true);
 translate ([20,60,240]) color([0.2,0.0,0.8]) cube([150,25,2]);
    
    translate ([205,50,-15]) color([0.7,0.7,0.7]) cube([15,20,15]);
    
   translate([32,55,-5]) color([0.7,0.7,0.7]) cylinder(5,d=15,center=true);
}
}

//TODO
module KWTUNER(x,y,z) {
translate([x,y,z]) {
    
        color([0.1,0.1,0.1]) cube([240,93,240]);
    
 translate ([50,55,240]) color([0.2,0.0,0.8]) cube([175,35,2]);
    
    translate ([205,50,-15]) color([0.7,0.7,0.7]) cube([15,20,15]);
    
   translate([32,55,-5]) color([0.7,0.7,0.7]) cylinder(5,d=15,center=true);
}
}

kiste(600,300,400);
//2m_TXRX(35,35,120);
bleiakku(35,200,30);
bleiakku(190,200,30);
bleiakku(345,200,30);
//KWTXRX(35,180,160);
//KWTUNER(280,180,160);