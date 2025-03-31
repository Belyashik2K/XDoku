from datetime import datetime
from sqlalchemy.orm import mapped_column, Mapped
from sqlalchemy import (
    func,
    ForeignKey,
)

from .base import Base

class Move(Base):
    __tablename__ = 'moves'

    id: Mapped[int] = mapped_column(primary_key=True)
    game_id: Mapped[int] = mapped_column(ForeignKey('games.id'), nullable=False)
    row: Mapped[int] = mapped_column(nullable=False)
    col: Mapped[int] = mapped_column(nullable=False)
    value: Mapped[int] = mapped_column(nullable=False)
    timestamp: Mapped[datetime] = mapped_column(nullable=False, default=datetime.now, server_default=func.now())