package controller

import (
	"backend/api/dto"
	// "backend/models"
	"backend/api/repository"
	"fmt"
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
	"github.com/go-playground/validator/v10"
)

type LEDController struct {
	Repo *repository.LedRepo
}

func NewLEDController() *LEDController {
	return &LEDController{
		Repo: repository.NewLEDRepo(),
	}
}

func (ledcontroller *LEDController) UpdateState(ctx *gin.Context) {
	id, err := strconv.Atoi(ctx.Param("id"))
	if err != nil {
		ctx.JSON(http.StatusBadRequest, gin.H{
			"message": err.Error(),
		})
	}

	req := new(dto.Request)
	if err := ctx.ShouldBindJSON(&req); err != nil {
		validationErrs, ok := err.(validator.ValidationErrors)
		if !ok {
			ctx.JSON(http.StatusBadRequest, "Invalid request")
			return
		}
		var errorMessage string
		for _, e := range validationErrs {
			errorMessage = fmt.Sprintf("error in field %s condition: %s", e.Field(), e.ActualTag())
			break
		}
		ctx.JSON(http.StatusBadRequest, errorMessage)
		return
	}

	if err = ledcontroller.Repo.UpdateState(uint(id), req.State); err != nil {
		ctx.JSON(http.StatusInternalServerError, gin.H{
			"message": err.Error(),
		})
		return
	}

	ctx.JSON(http.StatusOK, gin.H{
		"message": "status berhasil diperbarui",
	})

}

func (ledcontroller *LEDController) GetStatus(ctx *gin.Context) {
	leds, err := ledcontroller.Repo.GetStatus()
	if err != nil {
		ctx.JSON(http.StatusInternalServerError, gin.H{
			"message": err.Error(),
		})
		return
	}
	ctx.JSON(http.StatusOK, gin.H{
		"data": leds,
	})
	// return

}

func (ledcontroller *LEDController) ONAll(ctx *gin.Context) {
	err := ledcontroller.Repo.ONAll()
	if err != nil {
		ctx.JSON(http.StatusInternalServerError, gin.H{
			"message": err.Error(),
		})
		return
	}
	ctx.JSON(http.StatusOK, gin.H{
		"message": "sukses",
	})
	// return

}

func (ledcontroller *LEDController) OFFAll(ctx *gin.Context) {
	err := ledcontroller.Repo.OFFAll()
	if err != nil {
		ctx.JSON(http.StatusInternalServerError, gin.H{
			"message": err.Error(),
		})
		return
	}
	ctx.JSON(http.StatusOK, gin.H{
		"message": "sukses",
	})
	// return

}
