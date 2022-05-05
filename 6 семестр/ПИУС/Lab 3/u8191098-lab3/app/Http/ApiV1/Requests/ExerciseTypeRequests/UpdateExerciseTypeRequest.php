<?php

namespace App\Http\ApiV1\Requests\ExerciseTypeRequests;

use Illuminate\Foundation\Http\FormRequest;

class UpdateExerciseTypeRequest extends FormRequest
{
    public function rules(): array
    {
        return [
            'name' => 'unique:exercise_types,name|max:255',
        ];
    }
}
