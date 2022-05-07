<?php

namespace App\Http\ApiV1\Requests\SetRequests;

use Illuminate\Foundation\Http\FormRequest;

class CreateSetRequest extends FormRequest
{
    public function rules(): array
    {
        return [
            'exercise_id' => 'required|exists:exercises,id',
            'workout_id' => 'required|exists:workouts,id',
            'quantity' => 'nullable|integer',
            'time' => 'nullable|integer',
            'distance' => 'nullable|integer',
            'additional_weight' => 'nullable',
        ];
    }
}
