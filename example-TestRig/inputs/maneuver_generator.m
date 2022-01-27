close all;
clear all;

%% Input generator 

% file for the generation of the input time series for the virtual
% tire-test-rig


% time vector
t = 0:0.01:30; 
l = length(t);

en_x = 1; % enable input x as position rather than velocity
inputs.x = timeseries(ones(l,1) ,t);

en_y = 1; % enable input y as position rather than velocity
inputs.y = timeseries(zeros(l,1)+1,t);

en_z = 1; % enable input z as position rather than velocity
inputs.z = timeseries(ones(l,1).*0.1 + tire_data.UNLOADED_RADIUS,t);

en_theta_x = 1; % enable input theta_x as position rather than velocity
inputs.theta_x = timeseries(zeros(l,1),t);

en_theta_y = 1; % enable input theta_y as position rather than velocity
inputs.theta_y = timeseries(zeros(l,1),t);

en_theta_z = 1; % enable input theta_z as position rather than velocity
inputs.theta_z = timeseries(zeros(l,1),t);

inputs.omega = timeseries(ones(l,1)*10,t);
inputs.torque = timeseries(zeros(l,1),t);
inputs.Fz = timeseries(ones(l,1)* 1000,t);
inputs.pressure = timeseries(ones(l,1)* tire_data.INFLPRES,t);






en_torque = 0;