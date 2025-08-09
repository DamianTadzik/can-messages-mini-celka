%% Generate C source files from .dbc with cantools in the venv
% python -m cantools generate_c_source --use-float --database-name cmmc can_messages_mini_celka.dbc

database_name = 'cmmc';
dbc_file = 'test.dbc';

% Call the cantools from the venv
system(['"', fullfile(pwd, 'venv', 'Scripts', 'python.exe'), '" -m cantools generate_c_source --use-float --database-name ' database_name ' ' dbc_file]);

% Move generated files into src/
movefile([database_name '.c'], 'src');
movefile([database_name '.h'], 'src');


%% Generate code from template_decoder.c and name it %database_name%_can_decoder.c
decoder_name = generate_database_decoder(database_name);
% decoder_name = 'test_database_decoder';

%% Compile the mex function and copy it to src
mex_source_file = ['cmex\' decoder_name '.c'];

mex(mex_source_file, 'src\cmmc.c');

movefile([decoder_name '.mexw64'], 'src');

%% TESTS
addpath("src\");

test_database_decoder(uint32(32), uint8([0 2 0 0 0 2 0 0]))
ans.signals

clear test_database_decoder
