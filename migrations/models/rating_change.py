from datetime import datetime
from sqlalchemy.orm import mapped_column, Mapped
from sqlalchemy import (
    func,
    ForeignKey,
)

from .base import Base

class RatingChange(Base):
    __tablename__ = 'rating_history'

    id: Mapped[int] = mapped_column(primary_key=True)
    user_id: Mapped[int] = mapped_column(ForeignKey('users.id'), nullable=False)
    game_id: Mapped[int] = mapped_column(ForeignKey('games.id'), nullable=False)
    rating_change: Mapped[int] = mapped_column(nullable=False)
    new_rating: Mapped[int] = mapped_column(nullable=False)
    timestamp: Mapped[datetime] = mapped_column(nullable=False, default=datetime.now, server_default=func.now())