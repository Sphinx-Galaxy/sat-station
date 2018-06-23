module FAN() {
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