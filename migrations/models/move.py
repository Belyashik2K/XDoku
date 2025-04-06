from datetime import datetime
from sqlalchemy.orm import (
    mapped_column,
    Mapped,
)
from sqlalchemy import (
    func,
    ForeignKey,
)
from sqlalchemy.sql import expression

from .base import Base


class Move(Base):
    __tablename__ = 'moves'

    id: Mapped[int] = mapped_column(primary_key=True)
    game_id: Mapped[int] = mapped_column(
        ForeignKey('games.id', ondelete='CASCADE'),
        nullable=False
    )
    row: Mapped[int] = mapped_column(nullable=False)
    col: Mapped[int] = mapped_column(nullable=False)
    value: Mapped[int] = mapped_column(nullable=False)
    is_valid: Mapped[bool] = mapped_column(nullable=False, default=False, server_default=expression.false())
    timestamp: Mapped[datetime] = mapped_column(nullable=False, default=datetime.now, server_default=func.now())
