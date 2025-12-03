package routes

import (
	"backend/api/controller"
	"backend/middleware"
	"os"

	"github.com/gin-gonic/gin"
)

func ledRoute(r *gin.RouterGroup) {
	lc := controller.NewLEDController()

	r.POST("/state/:id", lc.UpdateState)
	r.GET("/state", lc.GetStatus)
	r.GET("/on", lc.ONAll)
	r.GET("/off", lc.OFFAll)
}

func IndexRoute(r *gin.Engine) {
	r.Use(middleware.CorsDefault())
	apiGroup := r.Group("/led")
	ledRoute(apiGroup)
	r.Run(":" + os.Getenv("PORT"))
}
