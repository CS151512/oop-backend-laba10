CREATE TABLE IF NOT EXISTS time_records (
    id SERIAL PRIMARY KEY,

    hours INTEGER NOT NULL CHECK (hours >= 0 AND hours < 24),
    minutes INTEGER NOT NULL CHECK (minutes >= 0 AND minutes < 60),
    seconds INTEGER NOT NULL CHECK (seconds >= 0 AND seconds < 60),

    formatted_time VARCHAR(8) NOT NULL,

    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_time_records_created_at ON time_records(created_at);