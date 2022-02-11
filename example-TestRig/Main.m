
clc;
close all;
clear all;
addpath(genpath('./lib'));
addpath(genpath('./tmp'));
addpath(genpath('./files_stl'));
addpath(genpath('./files_tir'));
addpath(genpath('./../sfun/virtualTestBench'));

% run setup for enve mex 
run('../toolbox/setup');

% Test name
test_name = 'sine_thetaX';

% sampling time 
Ts = 1e-3;

% Load Bus names
Simulink.importExternalCTypes('./../sfun/virtualTestBench/include_sfun/sfun_types.h');

% Read TIR data
tire_data = TIR_read('205_60_R15__left_debug.tir');

% Prepare input parameters
p1  = 20;                          % Ribs number
p2  = tire_data.UNLOADED_RADIUS;  % Shell radius on x axis (m) 
p3  = 9;                          % Shell curve degree for x axis 
p4  = 0.11;                        % Shell radius on y axis (m) 
p5  = 6;                          % Shell curve degree for y axis 
p6  = tire_data.WIDTH/2;          % Shell half width on y axis (m) 

p7  = 1;                          % method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
p8  = 0;                          % flat_enable 0: ENVE use ground::mesh (RDF), 1: ENVE use ground::flat

% ENVAR for TerrainServer
road_file = '../files_rdf/sample.rdf';
ground_path = [ pwd, '/', road_file];
setenv('ENVE_GROUND_PATH', ground_path);

% Actuation
actuation_type = 4; % 1-> fixed; 2-> spring; 3-> controlled_Fz_pid; 4-> controlled_Fz_loop;

switch actuation_type
    case 1
        Fz_forced = 0;
    case 2
        Fz_forced = 0;
    case 3
        Fz_forced = 0;
    case 4
        Fz_forced = 1;
end

% Tire configuration

% 0: Fz only, no Magic Formula evaluation;  
% 1: Fx,My only;  
% 2: Fy,Mx,Mz only;  
% 3: Fx,Fy,Mx,My,Mz uncombined force/moment calculation;  
% 4: Fx,Fy,Mx,My,Mz combined force/moment calculation;  
% 5: Fx,Fy,Mx,My,Mz combined force/moment calculation + turn slip;  
% +10: transient;  
% *-1: mirroring of tyre characteristics 
tire_use_mode = 15;

% Load the maneuver inputs
load('inputs/sine_thetaX.mat');

Tf = inputs.x.Time(end);

% create outputs folder
 mkdir(strcat('./outputs/', test_name));
 
% Start simulation 
fprintf('Starting Simulation -> %s \n', test_name)
tic;
model_sim = sim('TireTestRig');
toc;
fprintf('Simulation completed\n')

save(strcat('./outputs/',test_name,'/log'),'TTR_out','TTR_in');


