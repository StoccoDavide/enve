
clc;
clear all;
close all;

% Create shape and shell variables (hyperellipse)

tire_params.N  = 10;
tire_params.Rx = 0.5;
tire_params.Mx = 2.0;
tire_params.Ry = 0.2;
tire_params.My = 2.0;
tire_params.Ly = 0.1;

% Create shape and shell variables (polynom)

N  = 100;

S1002_radius = [ -2.63568, -2.60234, -2.56901, -2.53568, -2.50234, -2.46901, -2.43568, -2.40234, -2.36901, -2.33568, -2.30234, -2.26901, -2.23568, -2.20234, -2.16901, -2.13568, -2.10234, -2.06901, -2.03568, -2.00234, -1.96901, -1.93568, -1.90234, -1.86901, -1.83568, -1.80234, -1.76901, -1.73568, -1.70234, -1.66901, -1.63568, -1.60234, -1.56901, -1.53568, -1.50234, -1.46901, -1.43568, -1.40234, -1.36901, -1.33568, -1.30234, -1.26901, -1.23568, -1.20234, -1.16901, -1.13568, -1.10234, -1.06901, -1.03568, -1.00234, -0.96901, -0.93568, -0.90234, -0.86901, -0.83568, -0.80234, -0.76906, -0.73661, -0.70528, -0.67515, -0.64623, -0.61857, -0.59217, -0.56705, -0.54321, -0.52063, -0.49929, -0.47919, -0.46029, -0.44255, -0.42594, -0.41042, -0.39594, -0.38246, -0.36993, -0.35829, -0.34751, -0.33752, -0.32826, -0.31970, -0.31176, -0.30441, -0.29758, -0.29122, -0.28528, -0.27970, -0.27445, -0.26946, -0.26468, -0.26008, -0.25560, -0.25120, -0.24683, -0.24246, -0.23804, -0.23354, -0.22891, -0.22411, -0.21912, -0.21389, -0.20840, -0.20261, -0.19649, -0.19001, -0.18315, -0.17587, -0.16814, -0.15995, -0.15127, -0.14206, -0.13231, -0.12200, -0.11109, -0.09957, -0.08742, -0.07462, -0.06113, -0.04695, -0.03205, -0.01640, 0., 0.01719, 0.03518, 0.05400, 0.07366, 0.09419, 0.11561, 0.13795, 0.16122, 0.18545, 0.21067, 0.23689, 0.26415, 0.29246, 0.32187, 0.35238, 0.38404, 0.41688, 0.45092, 0.48620, 0.52276, 0.56062, 0.59984, 0.64044, 0.68247, 0.72598, 0.77102, 0.81762, 0.86585, 0.91577, 0.96743, 1.02090, 1.07624, 1.13354, 1.19287, 1.25430, 1.31794, 1.38388, 1.45222, 1.52308, 1.59656, 1.67281, 1.75195, 1.83413, 1.91952, 2.00827, 2.10058, 2.19664, 2.29665, 2.40085, 2.50947, 2.62278, 2.74101, 2.86453, 2.99361, 3.12861, 3.27009, 3.41886, 3.57605, 3.74306, 3.92157, 4.11353, 4.32109, 4.54658, 4.79251, 5.06153, 5.35655, 5.68073, 6.03766, 6.43153, 6.86750, 7.35159, 7.89212, 8.50059, 9.19409, 10.00000, 10.96772, 12.20121, 13.57495, 14.94869, 16.29070, 17.43125, 18.41121, 19.27588, 20.05196, 20.75676, 21.40228, 21.99725, 22.54824, 23.06038, 23.53771, 23.98353, 24.40054, 24.79101, 25.15684, 25.49966, 25.82085, 26.12163, 26.40303, 26.66598, 26.90871, 27.12430, 27.31371, 27.47824, 27.61895, 27.73669, 27.83216, 27.90588, 27.95826, 27.98958, 28.00000, 27.98958, 27.95826, 27.90588, 27.83216, 27.73669, 27.61895, 27.47824, 27.31371, 27.12430, 26.90871, 26.66536, 26.39230, 26.08712, 25.74679, 25.36750, 24.94651, 24.49424, 24.01064, 23.49245, 22.93567, 22.33526, 21.68478, 20.97570, 20.19634, 19.32997, 18.35102, 17.21666, 15.84381, 14.01926 ];
dataR = S1002_radius / 1000 + 0.3;
S1002_width  = [ -60.00000, -59.50000, -59.00000, -58.50000, -58.00000, -57.50000, -57.00000, -56.50000, -56.00000, -55.50000, -55.00000, -54.50000, -54.00000, -53.50000, -53.00000, -52.50000, -52.00000, -51.50000, -51.00000, -50.50000, -50.00000, -49.50000, -49.00000, -48.50000, -48.00000, -47.50000, -47.00000, -46.50000, -46.00000, -45.50000, -45.00000, -44.50000, -44.00000, -43.50000, -43.00000, -42.50000, -42.00000, -41.50000, -41.00000, -40.50000, -40.00000, -39.50000, -39.00000, -38.50000, -38.00000, -37.50000, -37.00000, -36.50000, -36.00000, -35.50000, -35.00000, -34.50000, -34.00000, -33.50000, -33.00000, -32.50000, -32.00000, -31.50000, -31.00000, -30.50000, -30.00000, -29.50000, -29.00000, -28.50000, -28.00000, -27.50000, -27.00000, -26.50000, -26.00000, -25.50000, -25.00000, -24.50000, -24.00000, -23.50000, -23.00000, -22.50000, -22.00000, -21.50000, -21.00000, -20.50000, -20.00000, -19.50000, -19.00000, -18.50000, -18.00000, -17.50000, -17.00000, -16.50000, -16.00000, -15.50000, -15.00000, -14.50000, -14.00000, -13.50000, -13.00000, -12.50000, -12.00000, -11.50000, -11.00000, -10.50000, -10.00000, -9.50000, -9.00000, -8.50000, -8.00000, -7.50000, -7.00000, -6.50000, -6.00000, -5.50000, -5.00000, -4.50000, -4.00000, -3.50000, -3.00000, -2.50000, -2.00000, -1.50000, -1.00000, -0.50000, 0.00000, 0.50000, 1.00000, 1.50000, 2.00000, 2.50000, 3.00000, 3.50000, 4.00000, 4.50000, 5.00000, 5.50000, 6.00000, 6.50000, 7.00000, 7.50000, 8.00000, 8.50000, 9.00000, 9.50000, 10.00000, 10.50000, 11.00000, 11.50000, 12.00000, 12.50000, 13.00000, 13.50000, 14.00000, 14.50000, 15.00000, 15.50000, 16.00000, 16.50000, 17.00000, 17.50000, 18.00000, 18.50000, 19.00000, 19.50000, 20.00000, 20.50000, 21.00000, 21.50000, 22.00000, 22.50000, 23.00000, 23.50000, 24.00000, 24.50000, 25.00000, 25.50000, 26.00000, 26.50000, 27.00000, 27.50000, 28.00000, 28.50000, 29.00000, 29.50000, 30.00000, 30.50000, 31.00000, 31.50000, 32.00000, 32.50000, 33.00000, 33.50000, 34.00000, 34.50000, 35.00000, 35.50000, 36.00000, 36.50000, 37.00000, 37.50000, 38.00000, 38.50000, 39.00000, 39.50000, 40.00000, 40.50000, 41.00000, 41.50000, 42.00000, 42.50000, 43.00000, 43.50000, 44.00000, 44.50000, 45.00000, 45.50000, 46.00000, 46.50000, 47.00000, 47.50000, 48.00000, 48.50000, 49.00000, 49.50000, 50.00000, 50.50000, 51.00000, 51.50000, 52.00000, 52.50000, 53.00000, 53.50000, 54.00000, 54.50000, 55.00000, 55.50000, 56.00000, 56.50000, 57.00000, 57.50000, 58.00000, 58.50000, 59.00000, 59.50000, 60.00000, 60.50000, 61.00000, 61.50000, 62.00000, 62.50000, 63.00000, 63.50000, 64.00000, 64.50000, 65.00000, 65.50000, 66.00000, 66.50000, 67.00000, 67.50000, 68.00000, 68.50000, 69.00000, 69.50000 ];
dataY = S1002_width / 1000;

%% Instantiate shape object

% obj = enve_shell(N, Rx, Mx, Ry, My, Ly);
obj = enve_shell(N, dataR', dataY');

% Test getters

obj.surfaceMaxRadius()
obj.surfaceMaxWidth()
obj.size()

% Test delete
% 
% obj.setRx(0.6);
% obj.setMx(2.1);
% obj.setRy(0.3);
% obj.setMy(2.1);
% obj.setLy(0.2);
% obj.reset(10);

obj

T = [ 0, 1, 0, 1.7; ...
      1, 0, 0, -140.0; ...
      0, 0, 1, 0.35; ...
      0, 0, 0, 1 ];

% obj.transform( T )
% obj.translate([0 0 0.26]')
% obj.rotate(pi/6, [1 0 0]')

% Set Color

rubber_color = [0.4 0.4 0.4];
road_color = [0.863 0.863 0.863];

% Test profile plot

out1 = figure;
obj.profile(out1, rubber_color)

%% Test 3D shell shape

out2 = figure;
subplot(1,2,1);
obj.shellShape(out2, rubber_color)
xlabel('x');
ylabel('y');
zlabel('z');

subplot(1,2,2);
obj.plotShape(out2, rubber_color)
xlabel('x');
ylabel('y');
zlabel('z');


% Test 3D shell tirex

out3 = figure;
subplot(1,2,1);
obj.shellTireX(out3, rubber_color)
xlabel('x');
ylabel('y');
zlabel('z');

subplot(1,2,2);
obj.plotTireX(out3, rubber_color)
xlabel('x');
ylabel('y');
zlabel('z');

% Test 3D shell ribs

out4 = figure;
subplot(1,2,1);
obj.shellRibs(out4, rubber_color)
xlabel('x');
ylabel('y');
zlabel('z');

subplot(1,2,2);
obj.plotRibs(out4, rubber_color)
xlabel('x');
ylabel('y');
zlabel('z');

% Test setup

mesh = enve_mesh('../../files_rdf/Eight.rdf');
mesh2 = enve_mesh('../../files_rdf/Eight.rdf');
mesh.copy(mesh2)

tic
obj.setupMesh(mesh, T, 10000, 'triangle')
toc

% out5 = figure;
% mesh.plot(out5, road_color)
% obj.plotTireX(out5, rubber_color )
% obj.plotSetup(out5, 'hsv')

%% Create flat

T = [ 0, 1, 0, 0.0; ...
      1, 0, 0, 0.0; ...
      0, 0, 1, 0.28; ...
      0, 0, 0, 1 ];

flat = enve_flat([0 0 0]', [0 0 1]', 1.0);

obj.setupFlat(flat, T)

obj.contactPointRibAvg()

out6 = figure;
flat.plot(out6, road_color)
obj.plotTireX(out6, rubber_color )
obj.plotSetup(out6, 'hsv')
