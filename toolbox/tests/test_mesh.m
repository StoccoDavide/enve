clc;
clear all;
close all;

%% Create mesh from *.rdf

m1 = enve_mesh('../../files_rdf/LakeTown.rdf');

m1.getTriangleground(1);

% % Plot output

out1 = figure;
m1.plot(out1, [0.863 0.863 0.863])

%% Create mesh from *.obj

m2 = enve_mesh('../../files_obj/sample.obj', 1.0);

m2.getTriangleground(1);

% % Plot output

out2 = figure;
m2.plot(out2, [0.863 0.863 0.863])
