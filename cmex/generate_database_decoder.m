function decoder_name = generate_database_decoder(database_name)
    header_information = extract_header_information(['src/' database_name '.h'], database_name);

    %% Read the template
    fid = fopen('template_database_decoder.c', 'rt');
    template = fread(fid, '*char')';
    fclose(fid);

    %% Get the case pattern from the template
    templateCasePattern = '(?m)^\s*\/\/ \/\/[^\n]*(?:\n\s*\/\/ \/\/[^\n]*)*';
    templateCase = regexp(template, templateCasePattern, 'match', 'once');
    if (isempty(templateCase))
        error('Could not find the case pattern in the template. This particular case should be prefixed with "// // " characters!');
    end
    % Remove the '// // ' prefix from each line (replace with '')
    templateCase = regexprep(templateCase, '\/\/ \/\/ ', '');
        
    %% Copy templateCase n_cases times and fill each with appropriate content
    n_cases = numel(header_information);
    generatedCases = "";
    for n = 1:n_cases
        thisCase = populate_thisCase(templateCase, header_information(n));
        generatedCases = generatedCases + thisCase + newline;
    end

    %% Replace templateCase with generatedCases and save as new file
    template = regexprep(template, templateCasePattern, generatedCases);
    
    decoder_name = [database_name '_database_decoder'];
    fid = fopen(['cmex\' decoder_name '.c'], 'w');
    fwrite(fid, template);
    fclose(fid);
end


function thisCase = populate_thisCase(thisCase, information)

    FRAME_ID = information.frame_ids;
    thisCase = strrep(thisCase, '%FRAME_ID%', FRAME_ID);
    
    STRUCT_NAME = information.struct_names;
    thisCase = strrep(thisCase, '%STRUCT_NAME%', STRUCT_NAME);

    UNPACK_FUNCTION = information.unpack_functions;
    thisCase = strrep(thisCase, '%UNPACK_FUNCTION%', UNPACK_FUNCTION);

    LENGTH = information.lengths;
    thisCase = strrep(thisCase, '%LENGTH%', LENGTH);

    FRAME_NAME = information.frame_names;
    thisCase = strrep(thisCase, '%FRAME_NAME%', FRAME_NAME);

    padding = '            ';
    SIGNAL_NAMES_ORDERED = strjoin(append(padding,information.signal_names), ',\n        ');
    thisCase = strrep(thisCase, '%SIGNAL_NAMES_ORDERED%', SIGNAL_NAMES_ORDERED);

    N_SIGNALS = num2str(numel(information.signal_names));
    thisCase = strrep(thisCase, '%N_SIGNALS%', N_SIGNALS);
    
    DECODE = '';
    for n = 1:numel(information.signal_names)
        x = lower(strrep(FRAME_NAME, '_NAME', ''));
        d = lower(strrep(strrep(information.signal_names{1}, '_NAME', ''), [strrep(FRAME_NAME, '_NAME', '') '_'], ''));
        DECODE = sprintf('%ssignal_values[%d] = (double)%s_%s_decode(tmp.%s);\n                ',DECODE,n-1,x,d,d);
    end
    thisCase = strrep(thisCase, '%DECODE%', DECODE);
end


function information = extract_header_information(header_file, database_name)
    header_text = fileread(header_file);

    frame_ids = parse_frame_ids(header_text);

    struct_names = parse_struct_names(header_text);

    unpack_functions = parse_unpack_functions(header_text);
    
    lengths = parse_lengths(header_text);

    frame_names = parse_frame_names(header_text);

    signal_names = parse_signal_names(header_text, frame_names);

    % Array of structures 
    n = numel(frame_ids);
    information = struct('frame_ids', cell(n,1), ...
                         'struct_names', cell(n,1), ...
                         'unpack_functions', cell(n,1), ...
                         'lengths', cell(n,1), ...
                         'frame_names', cell(n,1), ...
                         'signal_names', cell(n,1) ...
                         );
    for i = 1:n
        information(i).frame_ids = frame_ids{i};
        information(i).struct_names = struct_names{i};
        information(i).unpack_functions = unpack_functions{i};
        information(i).lengths = lengths{i};
        information(i).frame_names = frame_names{i};

        information(i).signal_names = signal_names.(frame_names{i});
    end
end


function frame_ids = parse_frame_ids(text)
    pattern = '#define (\w+_FRAME_ID)';
    tokens = regexp(text, pattern, 'tokens');
    frame_ids = [tokens{:}];    % Flatten the result
end
function struct_names = parse_struct_names(text)
    pattern = 'struct (\w*) {';
    tokens = regexp(text, pattern, 'tokens');
    struct_names = [tokens{:}];    % Flatten the result
end
function unpack_functions = parse_unpack_functions(text)
    pattern = 'int (\w*_unpack)\(';
    tokens = regexp(text, pattern, 'tokens');
    unpack_functions = [tokens{:}];    % Flatten the result
end
function lengths = parse_lengths(text)
    pattern = '#define (\w+_LENGTH)';
    tokens = regexp(text, pattern, 'tokens');
    lengths = [tokens{:}];    % Flatten the result
end
function frame_names = parse_frame_names(text)
    pattern = '\/\* Frame Names\. \*\/([\s\S]*?)\/\* Signal Names\. \*\/';
    match = regexp(text, pattern, 'match', 'once');
    pattern = '#define (\w+_NAME)';
    tokens = regexp(match, pattern, 'tokens');
    frame_names = [tokens{:}];    % Flatten the result
end

function signal_names = parse_signal_names(text, frame_names)
    pattern = '\/\* Signal Names\. \*\/([\s\S]*?)\/\*\*';
    match = regexp(text, pattern, 'match', 'once');
    pattern = '#define (\w+_NAME)';
    tokens = regexp(match, pattern, 'tokens');
    mixed_signal_names = [tokens{:}];    % Flatten the result
    
    n = numel(frame_names);
    
    % Inicjuj strukturę wynikową (mapę nazw ramki do sygnałów)
    signal_names = struct();
    
    for i = 1:n
        % Usuń sufiks _NAME z nazwy ramki, np. 'MSG1_NAME' -> 'MSG1'
        msg_name = regexprep(frame_names{i}, '_NAME$', '');
        
        % Znajdź sygnały, które zawierają nazwę ramki (msg_name)
        matched_signals = {};
        for j = 1:numel(mixed_signal_names)
            if contains(mixed_signal_names{j}, msg_name)
                matched_signals{end+1} = mixed_signal_names{j};
            end
        end
        
        % Zapisz listę sygnałów do pola struktury dla danej ramki
        signal_names.(frame_names{i}) = matched_signals;
    end
end



function structs = parse_structs(text)
    % Wyciągnięcie struktur i ich ciał
    pattern = 'struct\s+(\w+)\s*\{([^}]*)\};';
    tokens = regexp(text, pattern, 'tokens');
    structs = struct();
    for i = 1:length(tokens)
        struct_name = tokens{i}{1};
        struct_body = tokens{i}{2};
        % Wyciągamy tylko nazwy pól (ostatnie słowo przed średnikiem)
        field_pattern = '\s*\w+\s*\**\s+(\w+)\s*;';
        field_names = regexp(struct_body, field_pattern, 'tokens');
        % Zamieniamy na listę stringów
        field_names = [field_names{:}];
        structs.(struct_name) = field_names;
    end
end
