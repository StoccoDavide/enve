
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

% sampling time 
Ts = 1e-3;
Tf = 30;

% Load Bus names
Simulink.importExternalCTypes('./../sfun/virtualTestBench/include_sfun/sfun_types.h');

% Read TIR data
tire_data = TIR_read('205_60_R15__left.tir');

% Prepare input parameters
p1  = 5;                          % Ribs number
p2  = tire_data.UNLOADED_RADIUS;  % Shell radius on x axis (m) 
p3  = 9;                          % Shell curve degree for x axis 
p4  = 0.1;                        % Shell radius on y axis (m) 
p5  = 6;                          % Shell curve degree for y axis 
p6  = tire_data.WIDTH/2;          % Shell half width on y axis (m) 

p7  = 1;                          % method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
p8  = 0;                          % flat_enable 0: ENVE use ground::mesh (RDF), 1: ENVE use ground::flat

% ENVAR for TerrainServer
road_file = '../files_rdf/sample.rdf';
ground_path = [ pwd, '/', road_file];
setenv('ENVE_GROUND_PATH', ground_path);


actuation_type = 1; % 1-> fixed; 2-> spring; 3-> controlled_Fz

max_iteration = 100;
threshold_Fz = 1;

