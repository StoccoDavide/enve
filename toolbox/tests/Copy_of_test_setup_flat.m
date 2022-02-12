
clc;
clear all;
close all;

% Create shape and shell variables

N  = 11;
Rx = 0.3130;
Mx = 9.0;
Ry = 0.11;
My = 6.0;
Ly = 0.1025;

%% Instantiate shape object

obj = enve_shell(N, Rx, Mx, Ry, My, Ly);

T = [ 1, 0, 0, 0.0; ...
      0, 1, 0, 0.0; ...
      0, 0, 1, 0.312; ...
      0, 0, 0, 1 ];

obj.transform( T )
% obj.translate([0 0 0.26]')
obj.rotate(pi/2, [0 1 0]')
%obj.rotate(pi/6, [1 0 0]')

T = obj.transformation()

% Set Color

rubber_color = [0.4 0.4 0.4];
road_color = [0.863 0.863 0.863];

% Test profile plot

% Test setup

flat = enve_flat([0 0 0]', [0 0 1]', 1.0);

obj.setupFlat(flat, T, 'geometric')

obj.contactPointAvg()
obj.contactDepthAvg()

out5 = figure;
flat.plot(out5, road_color);
obj.plotSetupVec(out5, 0.1);
obj.plotSetupAvg(out5, 0.5);
obj.plotEnve(out5, rubber_color, 0.5 );
