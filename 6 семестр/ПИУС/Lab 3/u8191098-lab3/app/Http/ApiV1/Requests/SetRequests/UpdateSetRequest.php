<?php

namespace App\Http\ApiV1\Requests\SetRequests;

use Illuminate\Foundation\Http\FormRequest;

class UpdateSetRequest extends FormRequest
{
    public function rules(): array
    {
        return [
            'exercise_id' => 'exists:exercises,id',
            'workout_id' => 'exists:workouts,id',
            'quantity' => 'nullable|integer',
            'time' => 'nullable|integer',
            'distance' => 'nullable|integer',
            'additional_weight' => 'nullable',
        ];
    }
}
