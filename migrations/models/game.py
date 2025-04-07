from datetime import datetime

from sqlalchemy.dialects.postgresql import JSONB
from sqlalchemy.orm import (
    mapped_column,
    Mapped,
)
from sqlalchemy.sql import expression
from sqlalchemy import (
    func,
    ForeignKey,
)

from .base import Base


class Game(Base):
    __tablename__ = 'games'

    id: Mapped[int] = mapped_column(primary_key=True)
    user_id: Mapped[int] = mapped_column(
        ForeignKey('users.id', ondelete='CASCADE'),
        nullable=False
    )
    board: Mapped[dict] = mapped_column(JSONB, nullable=False)
    solution: Mapped[dict] = mapped_column(JSONB, nullable=False)
    difficulty: Mapped[str] = mapped_column(nullable=False)
    mistakes_count: Mapped[int] = mapped_column(nullable=False, default=0, server_default='0')
    start_time: Mapped[datetime] = mapped_column(nullable=False, default=func.now(), server_default=func.now())
    end_time: Mapped[datetime] = mapped_column(nullable=True)
    status: Mapped[str] = mapped_column(nullable=False, default='in_progress', server_default='in_progress')
    exited_while_solved: Mapped[bool] = mapped_column(nullable=False, default=False, server_default=expression.false())