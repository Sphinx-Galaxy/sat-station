use <ZA10.scad>
use <KWTXRX.scad>
use <Bleiakku.scad>
use <KWTuner.scad>

ZA10();

translate([35,120,500]) rotate([-90,0,0])KWTXRX();
translate([280,120,475]) rotate([-90,0,0])KWTuner();

translate([35,300,40]) bleiakku();

