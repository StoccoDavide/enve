function ENVEsfun_Simulator4_makecfg(BuildInfo)
%ENVESFUN_SIMULATOR4_MAKECFG adds include and source directories to the BuildInfo object.

%    Simulink version    : 10.4 (R2021b) 14-May-2021
%    MATLAB file generated on : 21-Jul-2022 17:52:27

% Verify the Simulink version
verify_simulink_version();

% Get the current directory
currDir = pwd;

% Get the MATLAB search path, remove the toolbox sub-directories except LCT demos
matlabPath = legacycode.lct.util.getSearchPath();

% Declare cell arrays for storing the paths
allIncPaths = {};
allSrcPaths = {};

% Get the build type
isSimTarget = is_simulation_target();
allLibs = {};
% Get the serialized paths information
info = get_serialized_info();

% Call the helper
pathInfo = legacycode.lct.util.resolvePaths(info, isSimTarget==1, currDir, matlabPath);

% Concatenate known include and source directories
allIncPaths = RTW.uniquePath([allIncPaths pathInfo.IncPaths(:)']);
allSrcPaths = RTW.uniquePath([allSrcPaths pathInfo.SrcPaths(:)']);

% Concatenate Host or Target libraries
allLibs = RTW.uniquePath([allLibs pathInfo.LibFiles(:)']);

% Additional include directories
addIncludePaths(BuildInfo, correct_path_name(allIncPaths));

% Additional source directories
addSourcePaths(BuildInfo,  correct_path_name(allSrcPaths));

linkLibsObjs     = {};
sfcnLibMods      = {};
sfcnLibModsPaths = {};
numSfcnLibMods   = 0;
sfcn_group = 'Sfcn';

linkLibsObjs    = [ linkLibsObjs  correct_path_name(allLibs)];

for i=1:length(linkLibsObjs)
    numSfcnLibMods = numSfcnLibMods + 1;
    [sfcnLibModsPaths{numSfcnLibMods},libName,libExt] = fileparts(linkLibsObjs{i});

    sfcnLibMods{numSfcnLibMods} = [libName libExt];
end

if ~isempty(sfcnLibMods)
    % add them to the BuildInfo object.  note that these are all considered not
    % precompiled and are link only
    addLibraries(BuildInfo, sfcnLibMods, sfcnLibModsPaths,...
                           [], false, true, sfcn_group);

end

%% ------------------------------------------------------------------------
function info = get_serialized_info()

% Allocate the output structure array
info(1:1) = struct(...
    'SFunctionName', '',...
    'IncPaths', {{}},...
    'SrcPaths', {{}},...
    'LibPaths', {{}},...
    'SourceFiles', {{}},...
    'HostLibFiles', {{}},...
    'TargetLibFiles', {{}},...
    'singleCPPMexFile', false,...
    'Language', ''...
    );

info(1).SFunctionName = 'ENVEsfun_Simulator4';
info(1).IncPaths = {'../../lib/include'};
info(1).LibPaths = {'/usr/local/lib'};
info(1).HostLibFiles = {'../../lib/dll/libenve_osx.dylib'};
info(1).Language = 'C';

%% ------------------------------------------------------------------------
function verify_simulink_version()

% Retrieve Simulink version
slVerStruct = ver('simulink');
slVer = str2double(strsplit(slVerStruct.Version,'.'));
% Verify that the actual platform supports the function used
if slVer(1)<8 || (slVer(1)==8 && slVer(2)<7)
    DAStudio.error('Simulink:tools:LCTErrorBadSimulinkVersion', slVerStruct.Version)
end

%% ------------------------------------------------------------------------
function pathSet = correct_path_name(pathSet)

for ii = 1:numel(pathSet)
    pathSet{ii} = coder.make.internal.transformPaths(pathSet{ii});
end
pathSet = RTW.uniquePath(pathSet);

%% ------------------------------------------------------------------------
function isSimTarget = is_simulation_target()

% Default output value
isSimTarget = 0;

% Get the current model and the code generation type to decide
% if we must link with the host libraries or with the target libraries
try
    modelName = get_param(0, 'CurrentSystem');
    if ~isempty(modelName)
        modelName = bdroot(modelName);
        sysTarget = get_param(modelName, 'RTWSystemTargetFile');
        isSimTarget = ~isempty([strfind(sysTarget, 'rtwsfcn') strfind(sysTarget, 'accel')]);

        mdlRefSimTarget = get_param(modelName,'ModelReferenceTargetType');
        isSimTarget = strcmpi(mdlRefSimTarget, 'SIM') || isSimTarget;

        % Verify again it's not Accelerator
        if ~isSimTarget
            simMode = get_param(modelName, 'SimulationMode');
            simStat = get_param(modelName, 'SimulationStatus');
            isSimTarget = strcmp(simStat, 'initializing') & strcmp(simMode, 'accelerator');
        end
    end
catch
end
