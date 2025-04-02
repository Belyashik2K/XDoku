from datetime import datetime
from sqlalchemy.orm import (
    mapped_column,
    Mapped,
)
from sqlalchemy import (
    func,
    ForeignKey,
    text,
)

from .base import Base


class Session(Base):
    __tablename__ = 'sessions'

    id: Mapped[int] = mapped_column(primary_key=True)
    user_id: Mapped[int] = mapped_column(ForeignKey('users.id'), nullable=False, unique=True)
    hwid: Mapped[str] = mapped_column(nullable=False)
    created_at: Mapped[datetime] = mapped_column(nullable=False, default=datetime.now, server_default=func.now())
    expires_at: Mapped[datetime] = mapped_column(nullable=False, server_default=text("(NOW() + INTERVAL '7 days')"))
