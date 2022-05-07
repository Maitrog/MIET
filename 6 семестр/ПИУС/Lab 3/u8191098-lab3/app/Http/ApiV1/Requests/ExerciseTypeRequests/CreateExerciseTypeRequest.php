<?php

namespace App\Http\ApiV1\Requests\ExerciseTypeRequests;

use Illuminate\Foundation\Http\FormRequest;

class CreateExerciseTypeRequest extends FormRequest
{
    public function rules(): array
    {
        return [
            'name' => 'required|unique:exercise_types,name|max:255',
        ];
    }
}
