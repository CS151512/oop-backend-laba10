CREATE TABLE IF NOT EXISTS math_operations (
    id SERIAL PRIMARY KEY,

    operation_name VARCHAR(100) NOT NULL,

    input_data JSONB NOT NULL,

    result VARCHAR(255) NOT NULL,

    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_math_operations_name ON math_operations(operation_name);
CREATE INDEX idx_math_input_data ON math_operations USING GIN (input_data);