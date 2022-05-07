<?php

namespace App\Http\ApiV1\Requests\WorkoutRequests;

use Illuminate\Foundation\Http\FormRequest;

class PatchWorkoutRequest extends FormRequest
{
    public function rules() : array
    {
        return [
            'date' => 'date|before:tomorrow',
            'duration' => 'nullable',
            'calories' => 'nullable',
            'max_puls' => 'nullable',
            'avg_puls' => 'nullable',
        ];
    }
}
