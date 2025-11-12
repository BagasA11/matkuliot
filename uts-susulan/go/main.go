package main

import (
	"backend/config"

	"backend/routes"

	"github.com/gin-gonic/gin"
	"github.com/joho/godotenv"
)

func main() {
	godotenv.Load()
	config.InitDB()

	r := gin.Default()
	routes.IndexRoute(r)
}
