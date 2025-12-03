package repository

import (
	"backend/config"
	"backend/models"
	"log"

	"gorm.io/gorm"
)

type LedRepo struct {
	DB *gorm.DB
}

func NewLEDRepo() *LedRepo {
	return &LedRepo{
		DB: config.DB,
	}
}

func (ledrepo *LedRepo) UpdateState(id uint, status string) error {
	// var led models.LED
	tx := config.DB.Begin()
	if err := tx.Model(&models.LED{}).Where("id = ?", id).
		Update("status", status).Error; err != nil {
		tx.Rollback()
		log.Fatal(err)
		return err
	}
	tx.Commit()
	return nil
}

func (ledrepo *LedRepo) ONAll() error {
	// var led models.LED
	tx := config.DB.Begin()
	if err := tx.Model(&models.LED{}).Where("status = ?", "OFF").
		Update("status", "ON").Error; err != nil {
		tx.Rollback()
		log.Fatal(err)
		return err
	}
	tx.Commit()
	return nil
}

func (ledrepo *LedRepo) OFFAll() error {
	// var led models.LED
	tx := config.DB.Begin()
	if err := tx.Model(&models.LED{}).Where("status = ?", "ON").
		Update("status", "OFF").Error; err != nil {
		tx.Rollback()
		log.Fatal(err)
		return err
	}
	tx.Commit()
	return nil
}

func (ledrepo *LedRepo) GetStatus() (led []models.LED, err error) {
	if err := ledrepo.DB.Select("status").Order("id asc").Find(&led).Error; err != nil {
		log.Fatal(err)
		return []models.LED{}, err
	}
	return led, nil
}
