<?php

namespace App\Http\ApiV1\Resources;

use Illuminate\Http\Resources\Json\JsonResource;

class ExerciseResource extends JsonResource
{
    public function toArray($request)
    {
        return [
            'id' => $this->id,
            'name' => $this->name,
            'exercise_type_id' => $this->exercise_type_id,
            'muscle_group_id' => $this->muscle_group_id,
        ];
    }
}
