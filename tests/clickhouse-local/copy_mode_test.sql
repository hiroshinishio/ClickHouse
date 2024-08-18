-- Test for clickhouse-local --copy mode

-- Create a JSON input file
CREATE FILE 'input.json' AS '{"key": "value"}\n{"key": "value2"}';

-- Run clickhouse-local with --copy mode
SYSTEM CALL 'clickhouse-local --copy < input.json > output.csv';

-- Check the output
SELECT * FROM file('output.csv', 'CSV', 'key String');
-- Expected output: value, value2
