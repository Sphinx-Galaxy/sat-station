module ZA10(){ difference() {
    color([0.1,0.4,0.0]) cube([600,400,500]);
    color([0.5,0.5,0.5]) translate([30,30,40]) cube([600-60,400-60,500]);
}
difference() {
color([0.1,0.4,0.0]) translate([0,400,500]) cube([600,30,400]);
color([0.5,0.5,0.5]) translate([10,400-10,500+10]) cube([600-20,30,400-20]);
}
}
 