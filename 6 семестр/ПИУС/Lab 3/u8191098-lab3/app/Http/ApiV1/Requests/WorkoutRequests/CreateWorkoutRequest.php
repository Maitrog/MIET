<?php

namespace App\Http\ApiV1\Requests\WorkoutRequests;

use Illuminate\Foundation\Http\FormRequest;

class CreateWorkoutRequest extends FormRequest
{
    public function rules(): array
    {
        return [
            'date' => 'date|before:tomorrow',
            'duration' => 'integer',
            'calories' => 'integer',
            'max_puls' => 'integer',
            'avg_puls' => 'integer',
        ];
    }
}
