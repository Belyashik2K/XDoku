from datetime import datetime
from sqlalchemy.orm import (
    mapped_column,
    Mapped,
)
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
    board: Mapped[str] = mapped_column(nullable=False)
    solution: Mapped[str] = mapped_column(nullable=False)
    difficulty: Mapped[int] = mapped_column(nullable=False)
    start_time: Mapped[datetime] = mapped_column(nullable=False, default=func.now(), server_default=func.now())
    end_time: Mapped[datetime] = mapped_column(nullable=True)
    status: Mapped[str] = mapped_column(nullable=False, default='active', server_default='active')
    exited_while_solved: Mapped[bool] = mapped_column(nullable=False, default=False, server_default='false')