function generate_decoder(database_name)
    header_file = ['src/' database_name '.h'];
    read_header(header_file, database_name);

    %% copy template and rename template
    
    %% Cut the case from it and use as a base?

    %% look for all %x%

end

%%
function read_header(header_file, database_name)
    header_text = fileread(header_file);


    frame_ids = parse_frame_ids(header_text);
    
    lengths = parse_lengths(header_text);

    unpacks = parse_unpacks(header_text);

    structs = parse_structs(header_text);

    frame_names = parse_frame_names(header_text);

end

function frame_ids = parse_frame_ids(text)
    % Regex do znalezienia identyfikatorów kończących się na _FRAME_ID
    pattern = '#define\s+(\w+_FRAME_ID)\s*\(0x[0-9a-fA-F]+u\)';
    % Znajdź wszystkie dopasowania - zwraca cell array of cell arrays
    tokens = regexp(text, pattern, 'tokens');
    % Spłaszczamy wynik do zwykłej listy stringów
    frame_ids = [tokens{:}];
end

function frame_ids = parse_lengths(text)
    % Regex do znalezienia identyfikatorów kończących się na _LENGTH
    pattern = '#define\s+(\w+_LENGTH)\s*\([0-8]+u\)';
    % Znajdź wszystkie dopasowania - zwraca cell array of cell arrays
    tokens = regexp(text, pattern, 'tokens');
    % Spłaszczamy wynik do zwykłej listy stringów
    frame_ids = [tokens{:}];
end

function unpack_funcs = parse_unpacks(text)
    % Regex do znalezienia nazw funkcji typu: int <nazwa>_unpack(
    pattern = 'int\s+(\w+_unpack)\s*\(';
    % Znajdź wszystkie dopasowania i zwróć nazwy funkcji
    tokens = regexp(text, pattern, 'tokens');
    % Spłaszcz wynik do zwykłej listy stringów
    unpack_funcs = [tokens{:}];
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


function frame_names = parse_frame_names(text)
    % Pattern to extract block between /* Frame Names. */ and /* Signal Names. */
    block_pattern = '/\* Frame Names\. \*/(.*?)/\* Signal Names\. \*/';

    % Use 'dotall' to make dot match newline
    block_match = regexp(text, block_pattern, 'tokens', 'dotall');

    if isempty(block_match)
        frame_names = {};
        warning('Frame Names block not found');
        return;
    end

    frame_block = block_match{1}{1};

    % Extract macro names ending with _NAME (only macro names, no values)
    define_pattern = '#define\s+(\w+_NAME)\b';
    tokens = regexp(frame_block, define_pattern, 'tokens');

    % Flatten tokens
    frame_names = cellfun(@(c) c{1}, tokens, 'UniformOutput', false);
end
