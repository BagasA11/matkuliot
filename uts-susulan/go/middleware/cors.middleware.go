package middleware

import (
	"net/http"
	"time"

	"github.com/gin-contrib/cors"
	"github.com/gin-gonic/gin"
)

func EnableCors() gin.HandlerFunc {
	return func(ctx *gin.Context) {
		// ctx.Writer.Header().Set("Access-Control-Allow-Origin", "http://localhost:5173")
		ctx.Writer.Header().Set("Access-Control-Allow-Origin", "*")
		ctx.Writer.Header().Set("Access-Control-Allow-Credentials", "true")
		ctx.Writer.Header().Set("Access-Control-Allow-Methods", "OPTIONS, POST, DELETE, GET, PUT")
		ctx.Writer.Header().Set("Access-Control-Allow-Headers", "Content-Type, Content-Length, Accept-Encoding, X-CSRF-Token, Authorization, accept, origin, Cache-Control, X-Requested-With")
		// if ctx.Request.Method == "OPTIONS" {
		// 	fmt.Println("OPTIONS")
		// 	ctx.AbortWithStatus(200)
		// 	return
		// }
		ctx.Next()
	}
}

func CorsDefault() gin.HandlerFunc {
	config := cors.DefaultConfig()
	config.AllowAllOrigins = true
	config.AllowMethods = []string{"POST", "GET", "PUT", "DELETE", "OPTIONS"}
	config.AllowHeaders = []string{"Origin", "Access-Control-Allow-Origin", "Content-Type", "Authorization", "Accept", "User-Agent", "Cache-Control", "Pragma"}
	config.ExposeHeaders = []string{"Content-Length"}
	config.AllowCredentials = true
	config.AllowFiles = true
	config.OptionsResponseStatusCode = http.StatusOK
	config.MaxAge = 4 * time.Hour
	return cors.New(config)
}
