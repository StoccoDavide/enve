close all;
clear all;

%% Input generator 

% file for the generation of the input time series for the virtual
% tire-test-rig


name = 'standstill';

% time vector
t = 0:0.01:30; 
l = length(t);

en_x = 1; % enable input x as position rather than velocity
inputs.x = timeseries(ones(l,1) ,t);
inputs.x0 = 0; % initial condition for x in case of velocity signal

en_y = 1; % enable input y as position rather than velocity
inputs.y = timeseries(zeros(l,1)+1,t);
inputs.y0 = 0; % initial condition for y in case of velocity signal

en_z = 1; % enable input z as position rather than velocity
inputs.z = timeseries(ones(l,1).*0.25,t);
inputs.z0 = 0; % initial condition for z in case of velocity signal

en_theta_x = 1; % enable input theta_x as position rather than velocity
inputs.theta_x = timeseries(zeros(l,1),t);
inputs.theta_x0 = 0; % initial condition for theta_x in case of velocity signal

en_theta_y = 1; % enable input theta_y as position rather than velocity
inputs.theta_y = timeseries(zeros(l,1),t);
inputs.theta_y0 = 0; % initial condition for theta_y in case of velocity signal

en_theta_z = 1; % enable input theta_z as position rather than velocity
inputs.theta_z = timeseries(zeros(l,1),t);
inputs.theta_z0 = 0; % initial condition for theta_z in case of velocity signal

% wheel rotational speed
inputs.omega = timeseries(ones(l,1)*10,t);


en_torque = 0; % enable torque input at the wheel
inputs.torque = timeseries(zeros(l,1),t);% wheel torque [Nm]
inputs.omega0 = 0; % initial condition for omega in case of torque input

inputs.Fz = timeseries(ones(l,1)* 1000,t); % Reference for Fz in "controlled_Fz" simulations

en_pressure = 0;
inputs.pressure = timeseries(zeros(l,1),t); % tire pressure (Pa) 


%% save meneuver input data

save(strcat(name,'.mat'));




