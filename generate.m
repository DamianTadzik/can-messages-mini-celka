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


%% Compile the mex function and copy it to src

% mex_source_file = [database_name '_decoder'];
mex_source_file = 'test_decoder';

mex(['cmex\' mex_source_file '.c'], 'src\cmmc.c');

movefile([mex_source_file '.mexw64'], 'src');


%% TESTS

test_decoder(uint32(32), uint8([0 0 0 0 0 0 0 0]))
