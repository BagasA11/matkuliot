package config

import (
	"fmt"
	"log"
	"os"

	"backend/models"
	"strconv"

	"gorm.io/driver/mysql"

	"gorm.io/gorm"
)

var DB *gorm.DB

func mysqlLocalDsn() string {
	// user: user1; pass:1234; host:localhost; port: 3306; db:banturiset
	dsn := fmt.Sprintf("%s:%s@tcp(%s:%s)/%s?charset=utf8mb4&parseTime=True&loc=Local",
		os.Getenv("DB_UNAME"), os.Getenv("DB_PASS"), os.Getenv("DB_HOST"), os.Getenv("DB_PORT"), os.Getenv("DB_NAME"))
	// fmt.Println("dsn: ", dsn)
	return dsn
}

func InitDB() error {
	dsn := mysqlLocalDsn()
	var err error
	DB, err = gorm.Open(mysql.Open(dsn), &gorm.Config{PrepareStmt: true})
	if err != nil {
		log.Fatal(dsn)
		return err
	}
	ismigrate, err := strconv.ParseBool(os.Getenv("ISMIGRATE"))
	if err != nil {
		log.Fatal(err)
		return err
	}
	if !ismigrate {
		err = DB.AutoMigrate(&models.LED{})
		if err != nil {
			return err
		}
		if err = seeding(DB); err != nil {
			return err
		}
	}
	if err != nil {
		log.Fatal(err)
		return err
	}
	return nil
}

func seeding(db *gorm.DB) error {
	var leds = []models.LED{
		{ID: 1, Status: "off"},
		{ID: 2, Status: "off"},
		{ID: 3, Status: "off"},
		{ID: 4, Status: "off"},
	}

	tx := db.Begin()
	if err := tx.Create(&leds).Error; err != nil {
		tx.Rollback()
		log.Fatal(err)
		return err
	}
	tx.Commit()
	return nil
}
