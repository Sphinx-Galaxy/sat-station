//TODO
module KWTuner() {
translate([0,1,0]) color([0.1,0.1,0.1]) cube([240,240,93]);
    
translate ([50,0,55]) color([0.2,0.0,0.8]) cube([175,1,35]);
    
translate ([205,240,50]) color([0.7,0.7,0.7]) cube([15,20,15]);
    
translate([32,240,55]) color([0.7,0.7,0.7]) cylinder(5,d=15,center=true);
}

KWTuner();