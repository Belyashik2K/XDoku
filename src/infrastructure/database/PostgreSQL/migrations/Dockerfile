# Runs the Alembic migrations against the `postgres` compose service. Nothing here is meant
# to be pushed anywhere or run standalone - it only exists so `docker compose up` can apply
# migrations without requiring Python on the host. See docker-compose.yml's `migrations` service.
FROM python:3.12-slim

WORKDIR /migrations

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

ENTRYPOINT ["alembic"]
CMD ["upgrade", "head"]
