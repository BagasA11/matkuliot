package models

type LED struct {
	ID     uint   `gorm:"primaryKey" json:"id"`
	Status string `json:"status"`
}
