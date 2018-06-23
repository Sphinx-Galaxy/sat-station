//TODO Nachmessen, Rückseite
module 2m_TXRX() {
 color([0.1,0.1,0.1]) cube([335,130,325]);
    
 translate([140,75,325]) color([0.7,0.7,0.7]) cylinder(50,r=30,center=true);
 translate([220,50,325]) color([0.7,0.7,0.7]) cylinder(40,r=10,center=true);
 translate([260,50,325]) color([0.7,0.7,0.7]) cylinder(40,r=10,center=true);
 
 translate ([10,20,325]) color([0.2,0.0,0.8]) cube([80,100,2]);
}