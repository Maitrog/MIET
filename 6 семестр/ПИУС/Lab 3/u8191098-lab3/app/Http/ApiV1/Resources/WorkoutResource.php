<?php

namespace App\Http\ApiV1\Resources;

use Illuminate\Http\Resources\Json\JsonResource;

class WorkoutResource extends JsonResource
{
    public function toArray($request)
    {
        return [
            'id' => $this->id,
            'date' => date_format($this->date, 'Y-m-d'),
            'duration' => $this->duration,
            'calories' => $this->calories,
            'max_puls' => $this->max_puls,
            'avg_puls' => $this->avg_puls,
        ];
    }
}
