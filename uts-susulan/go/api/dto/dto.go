package dto

type Request struct {
	State string `json:"state" binding:"required"`
}
