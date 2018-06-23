module KWTXRX() {
translate([0,25,0]) {
    difference() {
    color([0.1,0.1,0.1]) cube([240,240,93]);
    color([0.2,0.2,0.2]) translate([10,90,78]) cube([220,150,15]);
}
}
for(i = [1:11])
    color([0.4,0.4,0.4]) translate([i*20,90,78]) cube([3,150,15]);

//TODO    
translate([160,25,30]) color([0.7,0.7,0.7]) rotate([90,0,0]) cylinder(25,r=23);

translate([12,250,12]) color([0.7,0.7,0.7]) rotate([90,0,0]) cylinder(5,d=16);

translate ([20,24,60]) color([0.2,0.0,0.8]) cube([150,1,25]);
    
translate ([205,240,50]) color([0.7,0.7,0.7]) cube([15,20,15]);
}

KWTXRX();