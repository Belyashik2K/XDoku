import os

try:
    from dotenv import load_dotenv

    load_dotenv()
except ImportError:
    pass

DB_USER = os.environ.get("XDOKU_DB_USER", "xdoku_owner")
DB_PASSWORD = os.environ.get("XDOKU_DB_PASSWORD", "xdoku_local_password")
DB_HOST = os.environ.get("XDOKU_DB_HOST", "localhost")
DB_PORT = os.environ.get("XDOKU_DB_PORT", "5432")
DB_NAME = os.environ.get("XDOKU_DB_NAME", "xdoku")

DATABASE_URL: str = (
    f"postgresql+psycopg2://{DB_USER}:{DB_PASSWORD}@{DB_HOST}:{DB_PORT}/{DB_NAME}"
)
