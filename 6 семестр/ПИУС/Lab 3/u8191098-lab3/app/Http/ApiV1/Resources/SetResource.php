<?php

namespace App\Http\ApiV1\Resources;

use Illuminate\Http\Resources\Json\JsonResource;

class SetResource extends JsonResource
{
    public function toArray($request)
    {
        return [
            'id' => $this->id,
            'exercise_id' => $this->exercise_id,
            'workout_id' => $this->workout_id,
            'quantity' => $this->quantity,
            'time' => $this->time,
            'distance' => $this->distance,
            'additional_weight' => $this->additional_weight,
        ];
    }
}
