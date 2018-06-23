module CTRL_PANEL() {
        color([0.25,0.2,0.05]) cube([75,125,3]);

    translate([25,25,3]) color([0.7,0.7,0.7]) cylinder(25,r=10,center=true);
 translate([50,25,3]) color([0.7,0.7,0.7]) cylinder(15,r=10,center=true);
        
  translate([25,50,3]) color([0.7,0.7,0.7]) cylinder(25,r=10,center=true);
 translate([50,50,3]) color([0.7,0.7,0.7]) cylinder(15,r=10,center=true);       
}